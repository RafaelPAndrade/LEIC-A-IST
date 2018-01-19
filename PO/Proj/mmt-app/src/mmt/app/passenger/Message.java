package mmt.app.passenger;

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
  public static String requestPassengerName() {
    return "Nome do passageiro: ";
  }

  /**
   * @return prompt for new identifier
   */
  public static String requestNewId() {
    return "Novo identificador: ";
  }

  /**
   * @param id
   * @return return error message for unknown passenger
   */
  public static String noSuchPassengerId(int id) {
    return "O passageiro com o identificador " + id + " não existe.";
  }

  /** Prevent instantiation. */
  private Message() {
    // EMPTY
  }

}
