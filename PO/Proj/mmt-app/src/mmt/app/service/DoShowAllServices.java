package mmt.app.service;

import mmt.TicketOffice;
import pt.tecnico.po.ui.Command;

import java.util.List;
//FIXME import other classes if necessary

/**
 * 3.2.1 Show all services.
 */
public class DoShowAllServices extends Command<TicketOffice> {

  /**
   * @param receiver
   */
  public DoShowAllServices(TicketOffice receiver) {
    super(Label.SHOW_ALL_SERVICES, receiver);
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    for(String s: _receiver.getAllServices()) {
      _display.add(s);
    }
    _display.display();
  }

}
