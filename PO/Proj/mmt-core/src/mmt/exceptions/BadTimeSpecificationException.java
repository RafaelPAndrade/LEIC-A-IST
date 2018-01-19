package mmt.exceptions;

/** Exception thrown when an invalid time specification is used. */
public class BadTimeSpecificationException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Bad time. */
  private String _time;

  /**
   * @param time
   */
  public BadTimeSpecificationException(String time) {
    _time = time;
  }

  /**
   * @return bad time
   */
  public String getTime() {
    return _time;
  }

}
