package mmt.app.service;

/** Menu entries for the services menu. */
@SuppressWarnings("nls")
public interface Label {

  /** 3.2 Menu title. */
  String TITLE = "Consulta de serviços";

  /** 3.2.1 Show all services. */
  String SHOW_ALL_SERVICES = "Mostrar todos os serviços";

  /** 3.2.2 Show service by number. */
  String SHOW_SERVICE_BY_NUMBER = "Mostrar serviço com um dado número";

  /** 3.2.3 Show services departing from station. */
  String SHOW_SERVICES_DEPARTING_FROM_STATION = "Mostrar serviços com início em estação";

  /** 3.2.4 Show services arriving at station. */
  String SHOW_SERVICES_ARRIVING_AT_STATION = "Mostrar serviços com término em estação";

}
