package mmt.app.main;

/** Menu entries for the main menu. */
@SuppressWarnings("nls")
public interface Label {

  /** Menu title. */
  String TITLE = "Menu principal";

  /** Reset the ticket office. */
  String RESET = "Reiniciar";

  /** Open existing ticket office. */
  String OPEN = "Abrir";

  /** Save state of ticket office. */
  String SAVE = "Guardar";

  /** Create new program. */
  String OPEN_SERVICES_MENU = "Consulta de serviços";

  /** Read existing program. */
  String OPEN_PASSENGERS_MENU = "Gestão de passageiros";

  /** Write program. */
  String OPEN_ITINERARIES_MENU = "Gestão de itinerários";

}