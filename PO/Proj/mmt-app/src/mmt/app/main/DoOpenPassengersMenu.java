package mmt.app.main;

import mmt.TicketOffice;
import mmt.app.passenger.PassengersMenu;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Menu;

/**
 * §3.1.2. Open menu for managing identifiers and expressions.
 */
public class DoOpenPassengersMenu extends Command<TicketOffice> {

  /**
   * @param receiver
   */
  public DoOpenPassengersMenu(TicketOffice receiver) {
    super(Label.OPEN_PASSENGERS_MENU, receiver);
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    Menu menu = new PassengersMenu(_receiver);
    menu.open();
  }

}
