package mmt.app.service;

import mmt.TicketOffice;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Menu;

/** Menu builder for operations on schedules. */
public class ServicesMenu extends Menu {

  /**
   * @param receiver
   */
  public ServicesMenu(TicketOffice receiver) {
    super(Label.TITLE, new Command<?>[] { //
        new DoShowAllServices(receiver), //
        new DoShowServiceByNumber(receiver), //
        new DoShowServicesDepartingFromStation(receiver), //
        new DoShowServicesArrivingAtStation(receiver), //
    });
  }

}
