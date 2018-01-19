package mmt.exceptions;

/** Exception thrown when an invalid date specification is used. */
public class BadDateSpecificationException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Bad date. */
  private String _date;

  /**
   * @param date
   */
  public BadDateSpecificationException(String date) {
    _date = date;
  }

  /**
   * @return bad date
   */
  public String getDate() {
    return _date;
  }

}
