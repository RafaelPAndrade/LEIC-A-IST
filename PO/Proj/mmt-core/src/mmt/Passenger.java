package mmt;


import java.io.Serializable;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

import java.time.Duration;



/** A customer of the TrainCompany, has Itineraries
 *  
 *  @see Itinerary
 *  @see TrainCompany
 */
public class Passenger implements Serializable, Comparable {

	/** The superclass for the type of the passenger */
	public abstract class PassengerType implements Serializable {
		/** Serial number for serialization. */
		private static final long serialVersionUID = 20178079L;
		/** The list of the passenger itineraries */
		protected List<Itinerary> _itineraries;
		/** The total cost of all the itineraries */
		protected double _totalPaid;

		/**
		 * The constructor of types
		 *
		 * @param itineraries the list of itineraries already traveled
		 * @param paid the total cost of all the itineraries
		 */
		public PassengerType(List<Itinerary> itineraries, double paid) {
			_itineraries = itineraries;
			_totalPaid = paid;
		}

		/**
		 * Gets the discount rate the passenger has
		 *
		 * @return a double with the discount rate
		 */
		public abstract double getDiscountRate();


		/**
		 * Adds an itinerary, updates the total cost, and eventually updates
		 * the type of the passenger
		 *
		 * @param itinerary the itinerary to travel
		 */
		public void addItinerary(Itinerary itinerary) {
			_totalPaid += itinerary.getBaseCost()*(1 - getDiscountRate());
			_itineraries.add(itinerary);
		}

		/**
		 * Gets how many itineraries the passenger has
		 *
		 * @return the number of itineraries
		 */
		public int getNumberOfItineraries() {
			return _itineraries.size();
		}

		/**
		 * Gets how much the passenger has paid
		 *
		 * @return the amount of money the passenger paid for all
		 * the itineraries
		 */
		public double getTotalPaid() {
			return _totalPaid;
		}


		/**
		 * Gets all itineraries the passenger has
		 *
		 * @return an read-only list of itineraries
		 */
		public List<Itinerary> getItineraries() {
			return Collections.unmodifiableList(_itineraries);
		}



		/**
		 * Helper method to calculate the value of the last n itineraries
		 * @param n the number of itineraries to consider
		 * @return the price of the last n itineraries, or all itineraries, if n is too big
		 */
		protected double calculatePriceLastItineraries(int n) {
			double res = 0;
			int last = _itineraries.size();
			int first = (last - n > 0) ? last-n : 0;
			for(Itinerary i : _itineraries.subList(first, last)) {
				res += i.getBaseCost();
			}
			return res;
		}

	}

	/** The basic passenger type */
	public class NormalType extends PassengerType {
		public NormalType(List<Itinerary> i, double p) {
			super(i,p);
		}
	
		/**
		 * The concrete implementation of buying an itinerary for this
		 * type of passenger.
		 *
		 * @see PassengerType#addItinerary(Itinerary)
		 */
		@Override
		public void addItinerary(Itinerary i) {
			super.addItinerary(i);
			double last10iter = calculatePriceLastItineraries(10);
			if(last10iter > 2500) {
				Passenger.this._type = new SpecialType(_itineraries,_totalPaid);
			} else if(last10iter > 250) {
				Passenger.this._type = new FrequentType(_itineraries, _totalPaid);
			}
		}


		/**
		 * Gets the discount rate the passenger has
		 *
		 * @return 0.0, in this type (no discount)
		 * @see PassengerType#getDiscountRate()
		 */
		public double getDiscountRate() { return 0; }


		/**
		 * Gets a string representation of the passenger category Normal
		 *
		 * @return "NORMAL", in this type
		 */
		@Override
		public String toString() { return "NORMAL"; }

	}

	/** The frequent passenger type */
	public class FrequentType extends PassengerType {
		public FrequentType(List<Itinerary> i, double p) {
			super(i,p);
		}
	
		/**
		 * The concrete implementation of buying an itinerary for this
		 * type of passenger.
		 *
		 * @see PassengerType#addItinerary(Itinerary)
		 */
		@Override
		public void addItinerary(Itinerary i) {
			super.addItinerary(i);
			double last10iter = calculatePriceLastItineraries(10);
			if(last10iter > 2500) {
				Passenger.this._type = new SpecialType(_itineraries, _totalPaid);
			} else if(last10iter <= 250) {
				Passenger.this._type = new NormalType(_itineraries, _totalPaid);
			}
		}

		/**
		 * Gets the discount rate the passenger has
		 *
		 * @return 0.15, in this type (15% of discount)
		 * @see PassengerType#getDiscountRate()
		 */
		public double getDiscountRate() { return 0.15; }


		/**
		 * Gets a string representation of the passenger category Frequente
		 *
		 * @return "FREQUENTE", in this type
		 */
		@Override
		public String toString() { return "FREQUENTE"; }

	}


	/** The special passenger type */
	public class SpecialType extends PassengerType {
		public SpecialType(List<Itinerary> i, double p) {
			super(i,p);
		}
	
		/**
		 * The concrete implementation of buying an itinerary for this
		 * type of passenger.
		 *
		 * @see PassengerType#addItinerary(Itinerary)
		 */
		@Override
		public void addItinerary(Itinerary i) {
			super.addItinerary(i);
			double last10iter = calculatePriceLastItineraries(10);
			if(last10iter <= 2500) {
		//		Passenger.this._type = new FrequentType(_itineraries, _totalPaid);
		//	} else if(last10iter <= 250) {
				Passenger.this._type = new NormalType(_itineraries, _totalPaid);
			}
		}


		/**
		 * Gets the discount rate the passenger has
		 *
		 * @return 0.5, in this type (50% of discount)
		 * @see PassengerType#getDiscountRate()
		 */
		public double getDiscountRate() { return 0.5; }


		/**
		 * Gets a string representation of the passenger category Especial
		 *
		 * @return "ESPECIAL", in this type
		 */
		@Override
		public String toString() { return "ESPECIAL"; }

	}


	/** Serial number for serialization. */
	private static final long serialVersionUID = 20178079L;
	/** The passenger name */
	private String _name;
	/** The passenger id */
	private int _passengerId;
	/** The total time the Passenger has traveled */
	protected Duration _timeTraveled;
	/** The type of passenger 
	 * @see Passenger.PassengerType
	 */ 
	private PassengerType _type;

	/**
	 * Creates a new Passenger, of the normal type
	 *
	 * @param name the name for the new passenger
	 * @param id the numeric id attributed to passenger
	 */
	public Passenger(String name, int id) {
		_name = name;
		_passengerId = id;
		_timeTraveled = Duration.ZERO;
		_type = new NormalType(new ArrayList<Itinerary>(), 0);
	}

	/** 
 	 * Gets the name 
 	 *
 	 * @return the name of the passenger
 	 */
	public String getName() {
		return _name;
	}

	/** Changes the name of this passenger
 	 *
 	 * @param newName the new name of the passenger
 	 */
	public void setName(String newName) {
		_name = newName;
	}

	/** 
	 * Gets the numeric id given to the passenger
 	 *  
 	 *  @return the numeric id of the passenger;
 	 */
	public int getId() {
		return _passengerId;
	}

	/**
	 * Gets the discount rate the passenger has
	 *
	 * @return a double with the discount rate
	 * @see Passenger.PassengerType#getDiscountRate()
	 */
	public double getDiscountRate() {
		return _type.getDiscountRate();
	}

	/**
	 * Adds an itinerary to the passenger
	 *
	 * @param i the itinerary to add
	 * @see Passenger.PassengerType#addItinerary(Itinerary)
	 */
	public void addItinerary(Itinerary i) {
		_type.addItinerary(i);
		_timeTraveled=_timeTraveled.plus(i.calculateTravelTime());
	}

	/**
	 * Gets how many itineraries the passenger has
	 *
	 * @return the number of itineraries
	 * @see Passenger.PassengerType#getNumberOfItineraries()
	 */
	public int getNumberOfItineraries() {
		return _type.getNumberOfItineraries();
	}
	/**
	 * Gets how much the passenger has paid
	 *
	 * @return the amount of money the passenger paid for all
	 * the itineraries
	 * @see Passenger.PassengerType#getTotalPaid()
	 */
	public double getTotalPaid() {
		return _type.getTotalPaid();
	}


	/**
	 * Gets all itineraries the passenger has
	 *
	 * @return an read-only list of itineraries
	 * @see Passenger.PassengerType#getItineraries()
	 */
	public List<Itinerary> getItineraries() {
		return _type.getItineraries();
	}

	/**
	 * Returns all itineraries the passenger has, in string representation
	 *
	 * @return the string representation of all the itineraries the
	 * passenger has, with a header with name and id of the passenger;
	 * an empty string if the passenger has no itineraries
	 * @see Itinerary
	 */
	public String showItineraries() {
		String res = new String();
		if(getNumberOfItineraries() > 0) {
			res += String.format("== Passageiro %d: %s ==\n",
			       _passengerId, _name);
			List<Itinerary> itineraries = new ArrayList<>(getItineraries()); 
			itineraries.sort(null);
			for(int i = 0; i < getNumberOfItineraries(); ++i)
				res += itineraries.get(i).toString(i+1);
		}
		return res;
	}


	/**
	 * Compares 2 passengers by id
	 *
	 * @return the diference between ids
	 */
	@Override
	public int compareTo(Object o) throws ClassCastException, NullPointerException {
		Passenger p = (Passenger) o;
		return _passengerId - p._passengerId;
	}

	/**
	 * Gets the string representation of the passenger
	 *
	 * @return the textual representation of the passenger
	 */
	@Override
	public String toString() {
		return String.format("%d|%s|%s|%d|%.02f|%02d:%02d\n", _passengerId, _name,
		                     _type.toString(), getNumberOfItineraries(), getTotalPaid(),  
		                     _timeTraveled.toHours(), _timeTraveled.toMinutes() % 60);
	}
}
