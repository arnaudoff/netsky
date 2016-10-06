import { Injectable } from '@angular/core';
import { IConfigurableEntity } from './configurable-entity.interface';

/**
 * This class provides the SnifferConfigBuilder service to
 * incrementally build the config object.
 */
@Injectable()
export class SnifferConfigBuilderService {
  private interfaces: IConfigurableEntity;
  private filters: IConfigurableEntity;
  private shared: IConfigurableEntity;

  /**
   * Creates a new SnifferConfigBuilderService with default values.
   * @constructor
   */
  constructor() {
      this.interfaces = { values: [""] };
      this.filters = { values: [""] };
      this.shared = { values: [""] };
  }

  set_interfaces(interfaces: IConfigurableEntity): void {
      this.interfaces = interfaces;
  }

  set_filters(filters: IConfigurableEntity): void {
      this.filters = filters;
  }

  set_shared(shared: IConfigurableEntity): void {
      this.shared = shared;
  }

}
