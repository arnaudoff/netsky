import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';

import { Config } from '../config/env.config';
import { WebSocketService } from './../websocket/index';

@Injectable()
export class SnifferService {

  private _interfaces: Array<string>;
  private _filters: Array<string>;

  private _remoteConnection: Subject<Object>;

  constructor(private wsService: WebSocketService) {
    this._interfaces = [];
    this._filters = [];

    this._remoteConnection = <Subject<Object>>this.wsService
      .connect(Config.WS_SERVER_ADDRESS)
      .map((response: MessageEvent) : Object => {
        return JSON.parse(response.data);
      });
  }

  public addInterface(interfaceName: string) {
      this._interfaces.push(interfaceName);
  }

  public get interfaces() : Array<string> {
      return this._interfaces;
  }

  public addFilter(filterExpression: string) {
      this._filters.push(filterExpression);
  }

  public get filters() : Array<string> {
      return this._filters;
  }

  public retrieveInterfaces() : void {
    this.wsService.activeConnection.subscribe((v: Object) => {
        this._remoteConnection.next({ "retrieve-interfaces": {} });
    });
  }

  public start(): void {
    let argumentsObject: Object = {
      interfaces: this.interfaces,
      filters: this.filters,
      shared: [] // TODO: Remove
    };

    let commandObject: Object = {
        "start-sniffer": argumentsObject
    };

    this._remoteConnection.next(commandObject);
  }

}
