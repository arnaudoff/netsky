import { Injectable } from '@angular/core';
import { IConfigurableEntity } from './configurable-entity.interface';

/**
 * This class provides the SnifferConfigBuilder service to
 * incrementally build the config object.
 */
@Injectable()
export class SnifferConfigBuilderService {
  private interfaces_: IConfigurableEntity;
  private filters_: IConfigurableEntity;
  private listeners_: IConfigurableEntity;

  /**
   * Creates a new SnifferConfigBuilderService with default values.
   * @constructor
   */
  constructor() {
      this.interfaces_ = { values: ["any"] };
      this.filters_ = { values: [""] };
      this.listeners_ = { values: [""] };
  }

  public set interfaces(interfaces: IConfigurableEntity) {
      this.interfaces_ = interfaces;
  }

  public get interfaces() : IConfigurableEntity {
      return this.interfaces_;
  }

  public set filters(filters: IConfigurableEntity) {
      this.filters_ = filters;
  }

  public get filters() : IConfigurableEntity {
      return this.filters_;
  }

  public set listeners(listeners: IConfigurableEntity) {
      this.listeners_ = listeners;
  }

  public get listeners(): IConfigurableEntity {
      return this.listeners_;
  }

}
