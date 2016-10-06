import { Injectable } from '@angular/core';
import { ConfigurableEntity } from './configurable-entity';
import { ISnifferConifg } from './sniffer-config.interface';

/**
 * This class provides the SnifferConfigBuilder service to
 * incrementally build the config object.
 */
@Injectable()
export class SnifferConfigBuilderService {
  private snifferConfig: ISnifferConfig;

  /**
   * Creates a new SnifferConfigBuilderService.
   * @constructor
   */
  constructor() {}

  /**
   * Adds a ConfigurableEntity to the internal list with the given key
   */
  add(key: string, value: ConfigurableEntity): void {
    this.configurationKeys.push(key);
    this.configurationValues.push(value);
  }

  /**
    * Gets the constructed internal object.
    */
  get(): Object {
    let result: Object = {};

    this.configurationKeys.forEach((key, index) => {
      result[key] = this.configurationValues[index];
    })

    return result;
  }
}
