package mmt;

import java.io.Serializable;


import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

import java.time.LocalTime;
import java.time.Duration;


/** A Service is a set of stations ordered by the time of departure 
 * @see Station
 */
public class Service implements Serializable, Comparable {
	
	/** Serial number for serialization. */
	private static final long serialVersionUID = 20178079L;
	/** The numeric id of the service */
	private int _serviceId;
	/** The cost of traveling from the first to the last station of the service */
	private double _totalCost;
	/** The schedule is a association between a time and a station */
	private TreeMap<LocalTime,Station> _schedule;

	/**
	 * Creates a new empty service
	 *
	 * @param id the numeric id of the service
	 * @param cost the total cost of the service
	 */
	public Service(int id, double cost) {
		_serviceId = id;
		_schedule = new TreeMap<LocalTime,Station>();
		_totalCost = cost;
	}

	/**
	 * Adds a station to the schedule, and adds this service to the station
	 * service list
	 *
	 * @param time the time of arrival to the station
	 * @param station the station arrived
	 */
	public void addStation(LocalTime time, Station station) {
		_schedule.put(time, station);
		station.addService(this, time);
	}


	/**
	 * Gets the id of the service
	 *
	 * @return the numerice service id
	 */
	public int getId() {
		return _serviceId;
	}


	/**
	 * Returns an unmodifiable list of all the stations, ordered by time
	 *
	 * @return the stations of the schedule of the service
	 */
	public List<Station> getStationList() {
		return Collections.unmodifiableList(new ArrayList<Station>(_schedule.values()));
	}

	/**
	 * Gets the next station
	 *
	 * @param station a station
	 * @return the station right after the one given as argument, or null if: 1) there is no
	 * such station on this service; 2)The given station was the last station
	 */
	public Station getNextStation(Station station) {
		List<Station> stationsPassing = getStationList(); 
		int index = stationsPassing.lastIndexOf(station);
		if(index == -1 || index == stationsPassing.size()-1) {
			return null;
		} else {
			return stationsPassing.get(index+1);
		}
	}




	/**
	 * Returns whether the service is a valid route betweem 2 stations
	 *
	 * @param station1 departure station
	 * @param station2 arrival station
	 * @return true if the service stops at station1 and station2 and 
	 * passes station1 before station2
	 */
	public boolean isConnectionBetweenStations(Station station1, Station station2) {
		if(!(_schedule.containsValue(station1) && _schedule.containsValue(station2))) {
			return false;
		}
		
		return station2.getServiceTime(this).compareTo(station1.getServiceTime(this)) > 0;

	}


	/**
	 * Returns the cost of traveling between 2 stations on this service
	 * *
	 * @param station1 departure station
	 * @param station2 arrival station
	 * @return the cost of traveling between station1 and station2
	 */
	public double getCostBetweenStations(Station station1, Station station2) {
		if(!(_schedule.containsValue(station1) && _schedule.containsValue(station2))) {
			return 0;
		}

		LocalTime firstStation = _schedule.firstKey();
		LocalTime lastStation = _schedule.lastKey();
		
		LocalTime tStation1 = station1.getServiceTime(this);
		LocalTime tStation2 = station2.getServiceTime(this);
		

		return _totalCost * ((double) Duration.between(tStation1, tStation2).toMinutes() /
		                     Duration.between(firstStation, lastStation).toMinutes());

	}


	/**
	 * Compares 2 services by id
	 *
	 * @return the numeric difference between ids
	 */
	@Override
	public int compareTo(Object o) throws ClassCastException, NullPointerException {
		Service s = (Service) o;
		return _serviceId - s._serviceId;
	}

	/**
	 * Gets a textual representation of the service
	 */ 
	@Override
	public String toString() {
		String res = String.format("Serviço #%d @ %.2f\n", _serviceId, _totalCost);
		for(LocalTime t: _schedule.navigableKeySet())
			res += String.format("%tR %s\n", t, _schedule.get(t));
		return res; 
	}

	/**
	 * Gets a textual representation of part of the service
	 *
	 * @param station1 the first station to present
	 * @param station2 the last station to present
	 */ 
	public String toString(Station station1, Station station2) {
		double cost = getCostBetweenStations(station1, station2);
		LocalTime tStation1 = station1.getServiceTime(this);
		LocalTime tStation2 = station2.getServiceTime(this);
		String res = String.format("Serviço #%d @ %.2f\n", _serviceId, cost);
		for(LocalTime t: _schedule.navigableKeySet().subSet(tStation1, true, tStation2, true))
			res += String.format("%tR %s\n", t, _schedule.get(t));
		return res; 
	}




}
