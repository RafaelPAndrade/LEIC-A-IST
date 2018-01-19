package mmt.app.passenger;

import mmt.TicketOffice;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Menu;

/**
 * Menu builder for passenger operations.
 */
public class PassengersMenu extends Menu {

  /**
   * @param receiver
   */
  public PassengersMenu(TicketOffice receiver) {
    super(Label.TITLE, new Command<?>[] { //
        new DoShowAllPassengers(receiver), //
        new DoShowPassengerById(receiver), //
        new DoRegisterPassenger(receiver), //
        new DoChangerPassengerName(receiver), //
    });
  }

}
