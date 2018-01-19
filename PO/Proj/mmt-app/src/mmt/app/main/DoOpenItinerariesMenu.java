package mmt.app.main;

import mmt.TicketOffice;
import mmt.app.itineraries.ItinerariesMenu;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Menu;

/**
 * §3.1.2. Open itineraries menu.
 */
public class DoOpenItinerariesMenu extends Command<TicketOffice> {

  /**
   * @param receiver
   */
  public DoOpenItinerariesMenu(TicketOffice receiver) {
    super(Label.OPEN_ITINERARIES_MENU, receiver);
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    Menu menu = new ItinerariesMenu(_receiver);
    menu.open();
  }

}
