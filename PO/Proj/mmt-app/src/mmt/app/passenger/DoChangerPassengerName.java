package mmt.app.passenger;

import mmt.TicketOffice;
import mmt.app.exceptions.DuplicatePassengerNameException;
import mmt.app.exceptions.NoSuchPassengerException;
import mmt.exceptions.NoSuchPassengerIdException;
import mmt.exceptions.NonUniquePassengerNameException;
import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

//FIXME import other classes if necessary

/**
 * §3.3.4. Change passenger name.
 */
public class DoChangerPassengerName extends Command<TicketOffice> {

  private Input<Integer> _passengerId;
  private Input<String> _newName;

  /**
   * @param receiver
   */
  public DoChangerPassengerName(TicketOffice receiver) {
    super(Label.CHANGE_PASSENGER_NAME, receiver);
    _passengerId = _form.addIntegerInput(Message.requestPassengerId()); 
    _newName = _form.addStringInput(Message.requestPassengerName());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    _form.parse();
    try {
      _receiver.changePassengerName(_passengerId.value(), _newName.value());
    } catch(NoSuchPassengerIdException e) {
      throw new NoSuchPassengerException(e.getId());
    } catch(NonUniquePassengerNameException e) {
      throw new DuplicatePassengerNameException(e.getName());
   }
  }
}
