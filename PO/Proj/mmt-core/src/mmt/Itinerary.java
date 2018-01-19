package mmt;

import java.io.Serializable;

import java.util.List;
import java.util.ArrayList;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.Duration;


/** 
 * An Itinerary is a group of Services and the Stations used to
 * switch between services
 *
 *
 * @see Station
 * @see Service
 */
public class Itinerary implements Serializable, Comparable {
	
	/** Serial number for serialization. */
	private static final long serialVersionUID = 20178079L;
	/** The date of the travel */
	private LocalDate _date;
	/** The list of services used */
	private List<Service> _servicesUsed;
	/** The stations used to switch between services*/
	private List<Station> _transferStations;
	/** The cost for the passenger, without discounts */
	private double _baseCost;

	/**
	 * Constructor
	 */
	public Itinerary(List<Service> s, List<Station> t, LocalDate date) {
		_servicesUsed = s;
		_transferStations = t;
		_date = date;
		_baseCost = calculateBaseCost();
	}

	/**
	 * Gets the date of the itinerary
	 *
	 * @return the date of the itinerary
	 */
	public LocalDate getDate() {
		return _date;
	}


	/**
	 * Gets the cost of the itinerary, with no discounts applied
	 *
	 * @return the cost of the travel, with discounts
	 */
	public double getBaseCost() {
		return _baseCost;
	}


	/**
	 * Calculates the cost of the travel, with no discounts
	 * (Helper function)
	 *
	 * @return the total cost of the travel
	 */
	private double calculateBaseCost() {
		double res = 0;
		for(int i=0; i < _servicesUsed.size(); ++i) {
			Service s = _servicesUsed.get(i);
			Station station1 = _transferStations.get(i);
			Station station2 = _transferStations.get(i+1);
			res += s.getCostBetweenStations(station1, station2);
		}

		return res;
	}


	/**
	 * Calculates the total time that the itinerary takes
	 *
	 * @return the duration of the travel; the time between the 
	 * first and last stations arrivals
	 */
	public Duration calculateTravelTime() {
		Station station1 = _transferStations.get(0);
		LocalTime start = station1.getServiceTime(_servicesUsed.get(0));
		Station station2 = _transferStations.get(_transferStations.size()-1);
		LocalTime end = station2.getServiceTime(_servicesUsed.get(_servicesUsed.size()-1));
		return Duration.between(start, end);
	}	

	/**
	 * Appends another itinerary to the current one
	 *
	 * @param i2 the itinerary to be appended
	 * @return true if the itinerary was successfully appended
	 */
	public boolean appendItinerary(Itinerary i2) {
		Station t1 = _transferStations.get(_transferStations.size()-1);
		Station t2 = i2._transferStations.get(0);
		Service s1 = _servicesUsed.get(_servicesUsed.size()-1);
		Service s2 = i2._servicesUsed.get(0);

		if(!(t1.equals(t2) && _date.equals(i2._date) && t1.isTransferStationBetweenServices(s1, s2))) {
			return false;
		}

		if(s1.equals(s2)) {
		// Mesmo serviço; apagar a estação intermédia
				_transferStations.remove(t1);
				_servicesUsed.addAll(i2._servicesUsed.subList(1,i2._servicesUsed.size()));
		} else {
		// Serviços diferentes
			_servicesUsed.addAll(i2._servicesUsed.subList(0,i2._servicesUsed.size()));
		}

		// Add all transfer stations, besides t2; new cost is the sum of costs
		_transferStations.addAll(i2._transferStations.subList(1,i2._transferStations.size()));
		_baseCost += i2._baseCost;
		return true;
	}


	/**
	 * Compares 2 itineraries 
	 *
	 * Criteria used (in order): date, hour of departure, hour of arrival, cost
	 *
	 */
	@Override
	public int compareTo(Object o) throws ClassCastException, NullPointerException {
		Itinerary i = (Itinerary) o;
		
		int res = _date.compareTo(i._date);

		if(res == 0) {
			Station d1 = _transferStations.get(0);
			LocalTime t1 = d1.getServiceTime(_servicesUsed.get(0));
			Station d2 = i._transferStations.get(0);
			LocalTime t2 = d2.getServiceTime(i._servicesUsed.get(0));
			res = t1.compareTo(t2);
		}

		if(res == 0) {
			Station a1 = _transferStations.get(_transferStations.size()-1);
			LocalTime t1 = a1.getServiceTime(_servicesUsed.get(_servicesUsed.size()-1));
			Station a2 = i._transferStations.get(i._transferStations.size()-1);
			LocalTime t2 = a2.getServiceTime(i._servicesUsed.get(i._servicesUsed.size()-1));
			res = t1.compareTo(t2);
		}

		if(res == 0) {
			if(_baseCost > i._baseCost)
				res = 1;
			else if(_baseCost < i._baseCost)
				res = -1;
		}

		return res;
	}


	/**
	 * Gets a textual representation of a itinerary
	 *
	 * @param itineraryOrder the number of the itinerary to display
	 * (whether it is the 1st, 2nd, ...)
	 *
	 * @return the string representation of the itinerary
	 */ 
	public String toString(int itineraryOrder) {
		String res = String.format("\nItinerário %d para %tF @ %.2f\n", itineraryOrder, _date, _baseCost);
		for(int i=0; i < _servicesUsed.size(); ++i) {
			Service s = _servicesUsed.get(i);
			Station station1 = _transferStations.get(i);
			Station station2 = _transferStations.get(i+1);
			res += s.toString(station1, station2);
		}

		return res; 
	}



}
