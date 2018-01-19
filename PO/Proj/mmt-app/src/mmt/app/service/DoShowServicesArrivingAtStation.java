package mmt.app.service;

import mmt.TicketOffice;
import mmt.exceptions.NoSuchStationNameException;
import mmt.app.exceptions.NoSuchStationException;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import java.util.List;
//FIXME import other classes if necessary

/**
 * 3.2.4 Show services arriving at station.
 */
public class DoShowServicesArrivingAtStation extends Command<TicketOffice> {

  //FIXME define input fields
  Input<String> _stationName;

  /**
   * @param receiver
   */
  public DoShowServicesArrivingAtStation(TicketOffice receiver) {
    super(Label.SHOW_SERVICES_ARRIVING_AT_STATION, receiver);
    //FIXME initialize input fields
    _stationName = _form.addStringInput(Message.requestStationName()); 
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    //FIXME implement command
    _form.parse();
    try {
      for(String s: _receiver.getServicesArrivingAtStation(_stationName.value()))
        _display.add(s);
      _display.display();
    } catch(NoSuchStationNameException e) {
      throw new NoSuchStationException(e.getName());
    } 
  }

}
