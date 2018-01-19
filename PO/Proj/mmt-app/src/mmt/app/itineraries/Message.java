package mmt.app.itineraries;

/** Messages for menu interactions. */
@SuppressWarnings("nls")
public final class Message {

  /**
   * @return prompt for identifier
   */
  public static String requestPassengerId() {
    return "Identificador do passageiro: ";
  }

  /**
   * @return prompt for name
   */
  public static String requestDepartureStationName() {
    return "Nome da estação de partida: ";
  }

  /**
   * @return prompt for name
   */
  public static String requestArrivalStationName() {
    return "Nome da estação de destino: ";
  }

  /**
   * @param name
   * @return error message
   */
  public static String noSuchStationName(String name) {
    return "A estação com o nome '" + name + "' não existe.";
  }

  /**
   * @return prompt for ISO 8601 date
   */
  public static String requestDepartureDate() {
    return "Data de partida (YYYY-MM-DD): ";
  }

  /**
   * @return prompt for time
   */
  public static String requestDepartureTime() {
    return "Hora de partida (HH:MM): ";
  }

  /**
   * @return prompt for itinerary choice
   */
  public static String requestItineraryChoice() {
    return "Número do itinerário: ";
  }

  /**
   * @param number
   * @return return error message for unknown id
   */
  public static String noSuchItinerary(int number) {
    return "O itinerário " + number + " não existe.";
  }

  /**
   * @param name
   * @return return error message for unknown section
   */
  public static String noSuchIdentifier(String name) {
    return "O identificador '" + name + "' não existe.";
  }

  /**
   * @param passengerId
   * @return error message
   */
  public static String noItineraries(int passengerId) {
    return "O passageiro " + passengerId + " não tem itinerários.";
  }

  /**
   * @param name
   * @param dependent
   * @return error message for identifier removal
   */
  public static String identifierInUse(String name, String dependent) {
    return "O identificador '" + name + "' está em uso na definição de '" + dependent + "'.";
  }

  /** Prevent instantiation. */
  private Message() {
    // EMPTY
  }

}
