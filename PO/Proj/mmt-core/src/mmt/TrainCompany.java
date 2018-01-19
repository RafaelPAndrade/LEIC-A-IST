package mmt;

import mmt.exceptions.BadDateSpecificationException;
import mmt.exceptions.BadEntryException;
import mmt.exceptions.BadTimeSpecificationException;
import mmt.exceptions.ImportFileException;
import mmt.exceptions.NoSuchDepartureException;
import mmt.exceptions.NoSuchPassengerIdException;
import mmt.exceptions.NoSuchServiceIdException;
import mmt.exceptions.NoSuchStationNameException;
import mmt.exceptions.NoSuchItineraryChoiceException;
import mmt.exceptions.NonUniquePassengerNameException;
import java.io.IOException;
import java.io.FileNotFoundException;

import java.io.Serializable;
import java.io.FileReader;
import java.io.BufferedReader;

import java.util.Map;
import java.util.TreeMap;

import java.util.List;
import java.util.ArrayList;


import java.util.Collections;
import java.time.LocalTime;
import java.time.LocalDate;
import java.util.Comparator;
import java.util.function.Predicate;



/**
 * A train company has schedules (services) for its trains and passengers that
 * acquire itineraries based on those schedules.
 */
public class TrainCompany implements Serializable {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 20178079L;

  /** The list of all registered passengers */
  private Map<Integer,Passenger> _passengers;

  /** Map containing all services, ordered by id */
  private Map<Integer,Service> _services;

  /** Map containing all stations, using their name as the key */
  private Map<String,Station> _stations;

  /** List of possible itineraries, from the last search */
  private List<Itinerary> _itinerariesFound;

  /** Passenger to whom the itinerary will be added */
  private int _customerId;


  /**
   * Constructs a new TrainCompany from scratch
   */
  TrainCompany() {
    _services = new TreeMap<Integer,Service>();
    _passengers = new TreeMap<Integer,Passenger>();
    _stations = new TreeMap<String,Station>();
  }

  /**
   * Constructs a new TrainCompany, with information on services
   *
   * @param services map with service information
   */
  TrainCompany(Map<Integer,Service> services) {
    _services = services;
    _passengers = new TreeMap<Integer,Passenger>();
    _stations = new TreeMap<String,Station>();
  }


  /* Direct getters */

  /* Services */

  /**
   * Gets all the services, in the form of a map.
   *
   * This method helps constructing a new TrainCompany, while preserving information about Services.
   *
   * @return a map with all known services
   * @see TicketOffice#reset()
   */
  public Map<Integer,Service> getServiceMap() {
    return _services;
  }

  /**
   * Gets a service specified by id
   *
   * @param serviceId the specified id
   * @return the service that matches the id
   * @throws NoSuchServiceIdException no service with the given id exists
   */
  public Service getServiceById(int serviceId) throws NoSuchServiceIdException {
    Service res = _services.get(serviceId);
    if(res == null) {
      throw new NoSuchServiceIdException(serviceId);
    }
    return res;
  }

  /**
   * Returns whether a service with the specified id exists
   *
   * @param serviceId the specified id
   * @return true if a service with the given id exists
   */
  public boolean hasServiceById(int serviceId) {
    return _services.containsKey(serviceId);
  }


  /**
   * Gets all services, in the form of a read-only list, sorted by id
   *
   * @return all the services
   */
  public List<Service> getListOfServices() {
    List<Service> res = new ArrayList<Service>(_services.values());
    res.sort(null);
    return Collections.unmodifiableList(res);
  }
 
  /* Passengers */

  /**
   * Gets a passenger specified by id
   *
   * @param passengerId the specified id
   * @return the passenger that matches the id
   * @throws NoSuchPassengerIdException no passenger with the given id exists
   */
  public Passenger getPassengerById(int passengerId) throws NoSuchPassengerIdException {
    Passenger res = _passengers.get(passengerId);
    if(res == null) {
      throw new NoSuchPassengerIdException(passengerId);
    }
    return res;
  }

  /**
   * Returns whether a passenger with the specified id exists
   *
   * @param passengerId the specified id
   * @return true if a passenger with the given id exists
   */
  public boolean hasPassengerById(int passengerId) {
    return _passengers.containsKey(passengerId);
  }


  /**
   * Gets all passengers, in the form of a read-only list, sorted by id
   *
   * @return all the registered passengers
   */
  public List<Passenger> getListOfPassengers() {
    List<Passenger> res = new ArrayList<Passenger>(_passengers.values());
    res.sort(null);
    return Collections.unmodifiableList(res);
  }


  /* Stations */

  /**
   * Gets a station specified by name
   *
   * @param stationName the specified name of the station
   * @return the station with the name specified
   * @throws NoSuchStationNameException no station with the given name exists
   */ 
  public Station getStation(String stationName) throws NoSuchStationNameException {
    Station res = _stations.get(stationName);
    if(res == null) {
      throw new NoSuchStationNameException(stationName);
    }
    return res;
  }

  /**
   * Returns whether a station with the specified name exists
   *
   * @param stationName the specified name
   * @return true if a station with the given name exists
   */
  public boolean hasStationByName(String stationName) {
    return _stations.containsKey(stationName);
  }


  /* Import file methods */


  /**
   * Imports information about services and passengers from a file
   *
   * @param filename name of the file to import
   * @see #registerPassenger(String)
   * @see #importService(String[])
   * @see #importItinerary(String[])
   */
  void importFile(String filename) throws ImportFileException{
    try {
      String line;
      BufferedReader in = new BufferedReader(new FileReader(filename));
      while((line = in.readLine())!= null) {
        String args[] = line.split("\\|");
        switch(args[0]) {
          case "PASSENGER":
            registerPassenger(args[1]);
            break;

          case "SERVICE":
            importService(args);
            break;

          case "ITINERARY":
            importItinerary(args);
            break;
        }
      }
    } catch(IOException|NonUniquePassengerNameException|NoSuchStationNameException|
            NoSuchServiceIdException|NoSuchPassengerIdException e) { 
      throw new ImportFileException(e);
    }
  }

  /**
   * Constructs a service and associated stations, based on a line of the imported file
   * (Helper function)
   *
   * @param line a line from the imported file, split by fields
   * @throws NoSuchStationNameException
   * @see #importFile(String)
   */
  private void importService(String[] line) throws NoSuchStationNameException {
    Service s = new Service(Integer.parseInt(line[1]), Float.parseFloat(line[2]));
    for(int i=3; i<line.length; i+=2) {
      if(!hasStationByName(line[i+1])) {
        Station st = new Station(line[i+1]);
        _stations.put(line[i+1], st);
      }
      s.addStation(LocalTime.parse(line[i]), getStation(line[i+1]));
    }
    _services.put(s.getId(), s);
  }

  /**
   * Constructs a itinerary, based on a line of the imported file
   * (Helper function)
   *
   * @param line a line from the imported file, split by fields
   * @throws NoSuchStationNameException
   * @throws NoSuchPassengerIdException
   * @throws NoSuchServiceIdException
   * @see #importFile(String)
   */
  private void importItinerary(String[] line)
    throws NoSuchStationNameException, NoSuchPassengerIdException, NoSuchServiceIdException {
    int passengerId = Integer.parseInt(line[1]);
    LocalDate date = LocalDate.parse(line[2]); 
    List<Service> serviceList = new ArrayList<Service>();
    List<Station> transferStations = new ArrayList<Station>();
  
    for(int i=3; i<line.length; ++i) {
      String field[] = line[i].split("/");
      serviceList.add(getServiceById(Integer.parseInt(field[0])));
      transferStations.add(getStation(field[1]));
      if( i+1 == line.length ) transferStations.add(getStation(field[2]));
    }

    Itinerary res = new Itinerary(serviceList, transferStations, date);
    getPassengerById(passengerId).addItinerary(res);
  }


   /* Passenger management*/

  /**
   * Registers a new passenger
   *
   * @param newName the name of the new passenger
   * @throws NonUniquePassengerNameException the name is already used in another passenger
   */ 
  public void registerPassenger(String newName)
    throws NonUniquePassengerNameException {
    Predicate<Passenger> pre = new Predicate<Passenger>() {
      public boolean test(Passenger p) {
        return p.getName().equals(newName);
      }
    };
    if(!findPassengers(pre).isEmpty()) {
      throw new NonUniquePassengerNameException(newName);
    } else {
       Passenger newP = new Passenger(newName, _passengers.size());
      _passengers.put(_passengers.size(), newP);
    }
  }

  /**
   * Changes the name of a existing passenger
   *
   * @param passengerId the id of the passenger
   * @param newName the new name for the passenger
   * @throws NonUniquePassengerNameException the name is already used in another passenger
   */
  public void changePassengerName(int passengerId, String newName)
    throws NonUniquePassengerNameException, NoSuchPassengerIdException {
    Predicate<Passenger> pre = new Predicate<Passenger>() {
      public boolean test(Passenger p) {
        return p.getName().equals(newName);
      }
    };
    if(!hasPassengerById(passengerId)) {
      throw new NoSuchPassengerIdException(passengerId);
    } else if(!findPassengers(pre).isEmpty()) {
      throw new NonUniquePassengerNameException(newName);
    } else {
      _passengers.get(passengerId).setName(newName);
    } 
  }


 /* Itinerary search and management methods */


  /**
   * Gets itinerary possibilities
   *
   * @param passengerId the passenger to whom the itinerary will be added
   * @param station1 the departure station
   * @param station2 the station of arrival
   * @param departureDate the date of the travel
   * @param departureTime the earliest time of departure, from the station of departure
   * @return a list of itinerary possibilities
   * @see #calculateItineraries(Station, Station, LocalDate, LocalTime)
   */ 
  public List<Itinerary> searchItineraries(int passengerId, Station station1, Station station2,
                                           LocalDate departureDate, LocalTime departureTime) {

    _customerId = passengerId;
    _itinerariesFound = calculateItineraries(station1, station2, departureDate, departureTime);
    return _itinerariesFound;
  }
 


  /**
   * Gets itinerary possibilities
   *
   * @param station1 the departure station
   * @param station2 the station of arrival
   * @param departureDate the date of the travel
   * @param departureTime the earliest time of departure, from the station of departure
   * @return a list of itinerary possibilities
   * @see #calculateItineraries(Station, Station, LocalDate, LocalTime)
   */ 
  private List<Itinerary> calculateItineraries(Station station1, Station station2,
                                               LocalDate departureDate, LocalTime departureTime) {

    List<Itinerary> direct = new ArrayList<>();
    List<Itinerary> indirect = new ArrayList<>();
    List<Service> servicePos = station1.getServicesPassingAfter(departureTime);

    for(Service s: servicePos) {
      List<Service> servicesUsed = new ArrayList<>();
      servicesUsed.add(s);
      List<Station> transferStations = new ArrayList<>();
      transferStations.add(station1);

      if(s.isConnectionBetweenStations(station1,station2)) {
        transferStations.add(station2);
        direct.add(new Itinerary(servicesUsed, transferStations, departureDate)); 

      } else { // Not a direct route, recursive search

        Station stopStation = s.getNextStation(station1);
	if(stopStation == null) {
		//No next station, dead end
		continue;
	}
        LocalTime stopTime = stopStation.getServiceTime(s);

        transferStations.add(stopStation);
        Itinerary partial1 = new Itinerary(servicesUsed, transferStations, departureDate);

        List<Itinerary> partialCandidates = calculateItineraries(stopStation, station2, departureDate, stopTime);

        if(partialCandidates.size() > 0) {
          partial1.appendItinerary(partialCandidates.get(0));
          indirect.add(partial1);
        }
      }
    }

    direct.sort(null);
    indirect.sort(null);
    direct.addAll(indirect);
    return direct;
  }



  /**
   * Adds one of the found itineraries to a specific passenger
   *
   * @param itineraryNumber the choosen itinerary (by number)
   * @throws NoSuchItineraryChoiceException the itinerary number is invalid
   */ 
  public void commitItinerary(int itineraryNumber)
    throws NoSuchItineraryChoiceException, NoSuchPassengerIdException {
    
    try {
      getPassengerById(_customerId).addItinerary(_itinerariesFound.get(itineraryNumber-1));
    } catch(IndexOutOfBoundsException e) {
      throw new NoSuchItineraryChoiceException(_customerId, itineraryNumber);
    }

  }



  /* Find methods*/

  /**
   * Finds services matching some criteria and sorts them
   *
   * @param servicePredicate a predicate that tests services
   * @param serviceComparator a comparator used to sort results
   * @return a list of services
   * @see #findServices(Predicate)
   * @see Predicate
   */ 
  public List<Service> findServices(Predicate<Service> servicePredicate, Comparator<Service> serviceComparator) {
    List<Service> res = findServices(servicePredicate);
    res.sort(serviceComparator);
    return res;
  }


  /**
   * Finds services matching a predicate's criteria
   *
   * @param servicePredicate a Predicate that tests services
   * @return a list of services
   * @see Predicate
   */
  public List<Service> findServices(Predicate<Service> servicePredicate) {
    List<Service> res = new ArrayList<Service>(_services.values());
    res.removeIf(servicePredicate.negate());
    return res;
  }


  /**
   * Finds passengers matching some criteria and sorts them
   *
   * @param passengerPredicate a predicate that tests passengers
   * @param passengerComparator a comparator used to sort results
   * @return a list of passengers
   * @see #findPassengers(Predicate)
   * @see Predicate
   */ 
  public List<Passenger> findPassengers(Predicate<Passenger> passengerPredicate, Comparator<Passenger> passengerComparator) {
    List<Passenger> res = findPassengers(passengerPredicate);
    res.sort(passengerComparator);
    return res;
  }

  /**
   * Finds passengers matching a Predicate's criteria
   *
   * @param passengerPredicate a Predicate that tests passengers
   * @return a list of passengers
   * @see Predicate
   */
  public List<Passenger> findPassengers(Predicate<Passenger> passengerPredicate) {
    List<Passenger> res = new ArrayList<Passenger>(_passengers.values());
    res.removeIf(passengerPredicate.negate());
    return res;
  }

}
