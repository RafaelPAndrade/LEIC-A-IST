package mmt.app.main;

import mmt.TicketOffice;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Menu;

/** Main menu. */
public class MainMenu extends Menu {

  /**
   * @param receiver
   */
  public MainMenu(TicketOffice receiver) {
    super(Label.TITLE, new Command<?>[] { //
        new DoReset(receiver), //
        new DoOpen(receiver), //
        new DoSave(receiver), //
        new DoOpenServicesMenu(receiver), //
        new DoOpenPassengersMenu(receiver), //
        new DoOpenItinerariesMenu(receiver), //
    });
  }

}
