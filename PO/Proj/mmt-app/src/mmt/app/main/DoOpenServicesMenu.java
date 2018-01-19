package mmt.app.main;

import mmt.TicketOffice;
import mmt.app.service.ServicesMenu;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Menu;

/**
 * §3.1.2. Open menu for managing identifiers and expressions.
 */
public class DoOpenServicesMenu extends Command<TicketOffice> {

  /**
   * @param receiver
   */
  public DoOpenServicesMenu(TicketOffice receiver) {
    super(Label.OPEN_SERVICES_MENU, receiver);
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    Menu menu = new ServicesMenu(_receiver);
    menu.open();
  }

}
