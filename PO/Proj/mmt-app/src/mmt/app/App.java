package mmt.app;

import static pt.tecnico.po.ui.Dialog.IO;

import mmt.TicketOffice;
import mmt.exceptions.ImportFileException;

import mmt.app.main.MainMenu;
import pt.tecnico.po.ui.Menu;

/**
 * Main driver for the travel management application.
 */
public class App {
  /**
   * @param args
   */
  public static void main(String[] args) {
    TicketOffice office = new TicketOffice();

    String datafile = System.getProperty("import"); //$NON-NLS-1$
    if (datafile != null) {
      try {
        office.importFile(datafile);
      } catch (ImportFileException e) {
        // no behavior described: just present the problem
        e.printStackTrace();
      }
    }

    Menu menu = new MainMenu(office);
    menu.open();

    IO.close();
  }

}
