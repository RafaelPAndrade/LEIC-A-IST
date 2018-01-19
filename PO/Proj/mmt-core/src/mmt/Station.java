package mmt;


import java.io.Serializable;

import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

import java.time.LocalTime;


/** A Station has a name, and has services that arrive
 * @see Service
 */
public class Station implements Serializable {
	

	/** Serial number for serialization. */
	private static final long serialVersionUID = 20178079L;
	/** The name of the station */
	private String _name;
	/** Set of services associated with a time */
	private Map<Service,LocalTime> _servicesPassing;


	/**
	 * Creates a new station
	 *
	 * @param name the name of the station
	 */
	public Station(String name) {
		_name = name;
		_servicesPassing = new HashMap<Service,LocalTime>();
	}

	/**
	 * Adds a service to the set of the services that stop at
	 * this station
	 *
	 * @param service a service that arrives to the station
	 * @param time the time of arrival
	 */
	public void addService(Service service, LocalTime time) {
		_servicesPassing.put(service, time);
	}
	
	/**
	 * Gets the station name
	 *
	 * @return the name of the stations
	 */
	public String getName() {
		return _name;
	}

	/**
	 * Gets the time a service arrives at the station
	 *
	 * @param service a service
	 * @return the time ser arrives at the station,
	 * null if it does not pass on this station
	 */  
	public LocalTime getServiceTime(Service service) {
		return _servicesPassing.get(service);
	}

	/**
	 * Gets the services that pass after and at a specified time at this station
	 *
	 * @param time the time to consider
	 * @return the list of services that we can still ride on if we are at the station
	 * at the specified time
	 */ 
	public List<Service> getServicesPassingAfter(LocalTime time) {
		List<Service> res = new ArrayList<Service>();
		for(Service s: _servicesPassing.keySet())
			if(!getServiceTime(s).isBefore(time))
				res.add(s);

		return res;
	}

	
	/**
	 * Returns if the station is a suitable transfer station between
	 * two services.
	 *
	 * A transfer station is a station where 2 services pass, and the 
	 * time of arrival of the first service is before the arrival of 
	 * the second service
	 *
	 * @param service1 the first service
	 * @param service2 the second service
	 * @return true if both service1 and service2 arrive at the station,
	 * and service1 arrival time is before service2 arrival time
	 */
	public boolean isTransferStationBetweenServices(Service service1, Service service2) {
		if(!(_servicesPassing.containsKey(service1) && _servicesPassing.containsKey(service2))) {
			return false;
		}
		
		return getServiceTime(service2).compareTo(getServiceTime(service1)) >= 0;

	}


	/** Gets the textual representation of the station */
	@Override
	public String toString() {
		return _name;
	}
	
	/** Compares with a object to see if they are the same station */
	@Override
	public boolean equals(Object o) {
		if(o instanceof Station) {
			Station s = (Station) o;
			return s._name == _name;
		} else {
			return false;
		}
	}

}
