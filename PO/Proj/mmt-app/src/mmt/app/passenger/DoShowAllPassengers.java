package mmt.app.passenger;

//import mmt.DefaultSelector;
//import mmt.DefaultVisitor;

import mmt.TicketOffice;
import pt.tecnico.po.ui.Command;

//FIXME import other classes if necessary

/**
 * §3.3.1. Show all passengers.
 */
public class DoShowAllPassengers extends Command<TicketOffice> {

  /**
   * @param receiver
   */
  public DoShowAllPassengers(TicketOffice receiver) {
    super(Label.SHOW_ALL_PASSENGERS, receiver);
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    for(String s: _receiver.getAllPassengers())
      _display.add(s);
    _display.display();
  }

}
