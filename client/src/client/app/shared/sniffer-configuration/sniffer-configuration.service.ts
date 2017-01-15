import { Injectable } from '@angular/core';

/**
 * This class provides an injectable service to incrementally build the config
 * object.
 */
@Injectable()
export class SnifferConfigurationService {
  private interfaces_: Array<string>;
  private filters_: Array<string>;
  private listeners_: Array<string>;

  /**
   * Creates a new SnifferConfigurationService with default values.
   * @constructor
   */
  constructor() {
      this.interfaces_ = [];
      this.filters_ = [];
      this.listeners_ = [];
  }

  public addInterface(interfaceName: string) {
      this.interfaces_.push(interfaceName);
  }

  public get interfaces() : Array<string> {
      return this.interfaces_;
  }

  public addFilter(filterExpression: string) {
      this.filters_.push(filterExpression);
  }

  public get filters() : Array<string> {
      return this.filters_;
  }

  public addListener(listener: string) {
      this.listeners_.push(listener);
  }

  public get listeners(): Array<string> {
      return this.listeners_;
  }
}
