package mmt;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import mmt.exceptions.BadDateSpecificationException;
import mmt.exceptions.BadTimeSpecificationException;
import mmt.exceptions.ImportFileException;
import mmt.exceptions.MissingFileAssociationException;
import mmt.exceptions.NoSuchPassengerIdException;
import mmt.exceptions.NoSuchServiceIdException;
import mmt.exceptions.NoSuchStationNameException;
import mmt.exceptions.NoSuchItineraryChoiceException;
import mmt.exceptions.NonUniquePassengerNameException;


import java.util.List;
import java.util.Comparator;
import java.util.function.Predicate;
import java.util.ArrayList;

import java.time.LocalTime;
import java.time.LocalDate;
import java.time.format.DateTimeParseException;



/**
 * Façade for handling persistence and other functions.
 */
public class TicketOffice {

  /** The object doing most of the actual work. */
  private TrainCompany _trains = new TrainCompany();

  /** File association to save/load contents */
  private String _saveFile;

  /** Whether there are unsaved changes */
  private boolean _changedSinceLastSave = true;


  /* File loading/saving methods */

  /**
   * Destroys the application data, except information on Services
   */ 
  public void reset() {
    _trains = new TrainCompany(_trains.getServiceMap());
    _saveFile = null;
  }

  /**
   * Deserializes _trains from a file, and associates to the application
   *
   * @param filename the name of the file to deserialize
   * @throws FileNotFoundException
   * @throws IOException
   * @throws ClassNotFoundException
   * @see #_saveFile
   */
  public void load(String filename) throws FileNotFoundException, IOException, ClassNotFoundException {
    ObjectInputStream in = new ObjectInputStream(new BufferedInputStream(new FileInputStream(filename)));
    _trains = (TrainCompany) in.readObject();
    in.close();
    _saveFile = filename;
  }


  /** Gets if there is any file associated with the application */
  public boolean hasSaveFile() {
    return _saveFile != null;
  }


  /**
   * Associates filename to _saveFile, and then serializes to that file
   *
   * @param filename the name of the file to be associated to the application
   * @throws FileNotFoundException
   * @throws IOException
   * @see #save()
   * @see #_saveFile
   */
  public void save(String filename) throws FileNotFoundException, IOException {
    _saveFile = filename;
    save();
  }

  /**
   * Serializes _trains to _saveFile
   *
   * @throws FileNotFoundException
   * @throws IOException
   * @see #_trains
   * @see #load(String)
   */
  public void save() throws FileNotFoundException, IOException {
    if(_changedSinceLastSave) {

      ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(_saveFile)));
      out.writeObject(_trains);
      out.close();
      _changedSinceLastSave = false;
    }
  }


  /**
   * Imports data about Services and Passengers from file
   *
   * @see TrainCompany#importFile(String)
   */ 
  public void importFile(String datafile) throws ImportFileException {
    _trains.importFile(datafile);
  }

  /* Command implementation */

  /* Services Menu*/

  /**
   * Gets all services stored by _trains
   *
   * @return all know services by _trains, in text format
   * @see Service
   * @see TrainCompany#getListOfServices()
   * @see #convertToStringList(List)
   */
  public List<String> getAllServices() {
    return convertToStringList(_trains.getListOfServices());
  }

   /**
   * Gets a service, specified by the numeric id
   *
   * @param serviceId the numeric id of the wanted service
   * @return a string representation of the service
   * @throws NoSuchServiceIdException the service does not exist
   * @see Service
   * @see TrainCompany#getServiceById(int)
   */
  public String getServiceById(int serviceId) throws NoSuchServiceIdException {
    return _trains.getServiceById(serviceId).toString();
  }


  /**
   * Gets all services arriving at a station, ordered by time at that station
   *
   * @param stationName the name of the station of arrival
   * @return all services that fulfill the conditions, in textual format
   * @throws NoSuchStationNameException the specified station does not exist
   * @see Service
   * @see #convertToStringList(List)
   */ 
  public List<String> getServicesArrivingAtStation(String stationName)
    throws NoSuchStationNameException {

    Station arrivalStation = _trains.getStation(stationName);
    Predicate<Service> arrivals = new Predicate<Service>() {
      public boolean test(Service s){
        List<Station> stationList = s.getStationList(); 
        return arrivalStation.equals(stationList.get(stationList.size()-1));
      }
    };

    Comparator<Service> byTime = new Comparator<Service>(){
      public int compare(Service s1, Service s2) {
        return arrivalStation.getServiceTime(s1).compareTo(arrivalStation.getServiceTime(s2));
      }
    };

    return convertToStringList(_trains.findServices(arrivals, byTime));
  } 


  /**
   * Gets all services departing from a station, ordered by time at that station
   *
   * @param stationName the name of the station of arrival
   * @return all services that fulfill the conditions, in textual format
   * @throws NoSuchStationNameException the specified station does not exist
   * @see Service
   * @see #convertToStringList(List)
   */ 
  public List<String> getServicesDepartingFromStation(String stationName)
    throws NoSuchStationNameException {

    Station departureStation =_trains.getStation(stationName);

    Predicate<Service> departures = new Predicate<Service>() {
      public boolean test(Service s){
        List<Station> stationList = s.getStationList(); 
        return departureStation.equals(stationList.get(0));
      }
    };

    Comparator<Service> byTime = new Comparator<Service>() {
      public int compare(Service s1, Service s2) {
        return departureStation.getServiceTime(s1).compareTo(departureStation.getServiceTime(s2));
      }
    };

    return convertToStringList(_trains.findServices(departures, byTime));
  }
 

  /* Passengers Menu */

  /**
   * Gets all passenger registered in _trains
   *
   * @return all know passengers stored in _trains, in text format
   * @see Passenger
   * @see #convertToStringList(List)
   */ 
  public List<String> getAllPassengers() {
    return convertToStringList(_trains.getListOfPassengers());
  }


  /**
   * Gets a passenger, specified by the numeric id
   *
   * @param passengerId the numeric id of the passenger
   * @return a string represention of the passenger
   * @throws NoSuchPassengerIdException no passenger with that id exists
   * @see Passenger
   */
  public String getPassengerById(int passengerId) throws NoSuchPassengerIdException {
    return _trains.getPassengerById(passengerId).toString();                          
  }


  /**
   * Register a new passenger with the specified name
   *
   * @param newName the name of the new passenger
   * @throws NonUniquePassengerNameException a passenger with the specified name already exists
   * @see Passenger
   */
  public void registerPassenger(String newName)
    throws NonUniquePassengerNameException {
      _trains.registerPassenger(newName);
      _changedSinceLastSave = true;
  }


  /**
   * Change a existing passenger's name
   *
   * @param id the numeric passsenger id of the passenger
   * @param newName the new name for the passenger
   * @throws NonUniquePassengerNameException a passenger with the specified name already exists
   * @throws NoSuchPassengerIdException the specified passenger does not exist
   * @see Passenger
   */
  public void changePassengerName(int id, String newName)
    throws NonUniquePassengerNameException, NoSuchPassengerIdException {
      _trains.changePassengerName((id), newName); 
      _changedSinceLastSave = true;
    }


  /* Itinerary Menu */

  /**
   * Gets all itineraries of passengers registered in _trains
   *
   * @return all itineraries of all the passengers, in text format
   * @see Itinerary
   * @see Passenger
   */ 
  public List<String> showAllItineraries() {
    Predicate<Passenger> pre = new Predicate<Passenger>() {
      public boolean test(Passenger p) {
        return p.getNumberOfItineraries() > 0;
      }
    };
    List<String> res = new ArrayList<String>();
    for(Passenger p: _trains.findPassengers(pre, null))
      res.add(p.showItineraries());

    return res;
  }

  /**
   * Gets all itineraries of a passenger
   *
   * @param passengerId the id of the passenger
   * @return all known itineraries of a passenger, in text format
   * @throws NoSuchPassengerIdException no passenger with that id exists
   * @see Itinerary
   * @see Passenger
   */ 
  public String showPassengerItineraries(int passengerId) throws NoSuchPassengerIdException {
    return _trains.getPassengerById(passengerId).showItineraries();
  }


  /**
   * Shows itinerary possibilities, and saves the passenger to which the itinerary
   * should be given
   *
   * @param passengerId the id of a passenger
   * @param departureStation the departure station name
   * @param arrivalStation the station of arrival name
   * @param departureDate the date of the travel (in string format)
   * @param departureTime the earliest time of departure, from the station of departure 
   * (in string format)
   * @return a list of Strings showing itinerary possibilities
   * @throws NoSuchPassengerIdException the passenger id is invalid
   * @throws NoSuchStationNameException the specified station does not exist
   * @throws BadDateSpeciticationException the date argument is wrongly formatted
   * @throws BadTimeSpeciticationException the time argument is wrongly formatted
   * @see TrainCompany#searchItineraries(int, Station, Station, LocalDate, LocalTime)
   */ 
  public List<String> searchItineraries(int passengerId, String departureStation, String arrivalStation, String departureDate, String departureTime)
    throws NoSuchPassengerIdException, NoSuchStationNameException, BadDateSpecificationException, BadTimeSpecificationException {

    // Verifying that both date and time are parseable
    try {
      LocalDate date = LocalDate.parse(departureDate);
    } catch(DateTimeParseException e) { throw new BadDateSpecificationException(departureDate); }
    try {
      LocalTime time = LocalTime.parse(departureTime);
    } catch(DateTimeParseException e) { throw new BadTimeSpecificationException(departureTime); }

    if(!_trains.hasPassengerById(passengerId)) {
      throw new NoSuchPassengerIdException(passengerId);
    }

    Passenger customer = _trains.getPassengerById(passengerId);
    Station station1 = _trains.getStation(departureStation);
    Station station2 = _trains.getStation(arrivalStation);
    LocalDate date = LocalDate.parse(departureDate);
    LocalTime time = LocalTime.parse(departureTime);

    List<Itinerary> possibilities = _trains.searchItineraries(passengerId, station1, station2, date, time); 
    List<String> res = new ArrayList<String>();
    for(int i=0; i < possibilities.size(); ++i) {
      res.add(possibilities.get(i).toString(i+1));
    }

    return res;
  }


  /**
   * Adds one of the found itineraries to the specified passenger
   * on searchItineraries
   *
   * @param itineraryNumber the choosen itinerary (by number)
   * @throws NoSuchItineraryChoiceException the itinerary number is invalid
   * @throws NoSuchPassengerIdException the passenger id is now invalid
   * @see TrainCompany#commitItinerary(int)
   */ 
  public void commitItinerary(int itineraryNumber) 
    throws NoSuchPassengerIdException, NoSuchItineraryChoiceException {
    _trains.commitItinerary(itineraryNumber);
  }


  /**
   * Handy method to convert lists of objects to their string representation
   *
   * @param entities list of objects to transform in strings, via toString
   * @return a list of strings
   */
  private List<String> convertToStringList(List<?> entities) {
    List<String> res = new ArrayList<String>(entities.size());
    for(Object e: entities)
      res.add(e.toString());
    return res;
  }



}
