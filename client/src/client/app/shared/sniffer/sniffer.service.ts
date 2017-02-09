import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';

import { Config } from '../config/env.config';
import { WebSocketService } from './../websocket/index';
import { HostInfo } from './host-info';
import { AuthenticationInfo } from './authentication-info';

@Injectable()
export class SnifferService {

  public hostInfo: Subject<HostInfo>;
  public authenticationInfo: Subject<AuthenticationInfo>;

  private _interfaceName: string;
  private _filterExpression: string;
  private _remoteConnection: Subject<Object>;

  constructor(private wsService: WebSocketService) {
    this._interfaceName = '';
    this._filterExpression = '';

    this._remoteConnection = <Subject<Object>>this.wsService
      .connect(Config.WS_SERVER_ADDRESS)
      .map((response: MessageEvent) : Object => {
        return JSON.parse(response.data);
      });

    this.hostInfo = <Subject<HostInfo>>this.wsService
      .connect(Config.WS_SERVER_ADDRESS)
      .map((response: MessageEvent) : HostInfo => {
        let data = JSON.parse(response.data);
        return <HostInfo>data;
      });

    this.authenticationInfo = <Subject<AuthenticationInfo>>this.wsService
      .connect(Config.WS_SERVER_ADDRESS)
      .map((response: MessageEvent) : AuthenticationInfo => {
        let data = JSON.parse(response.data);
        return <AuthenticationInfo>data;
      });
  }

  public set interfaceName(name: string) {
    this._interfaceName = name;
  }

  public get interfaceName() : string {
      return this._interfaceName;
  }

  public set filterExpression(expression: string) {
      this._filterExpression = expression;
  }

  public get filterExpression() : string {
      return this._filterExpression;
  }

  public retrieveInterfaces() : void {
    this._remoteConnection.next({ 'retrieve-interfaces': {} });
  }

  public sendHostCheck() : void {
    this.wsService.activeConnection.subscribe((v: Object) => {
        this._remoteConnection.next({ 'has-host': {} });
    });
  }

  public sendAuthenticate(password: string) {
    let argumentsObject: Object = {
      password: password,
    };

    let commandObject: Object = {
        'authenticate': argumentsObject
    };

    this._remoteConnection.next(commandObject);
  }

  public start(): void {
    let argumentsObject: Object = {
      'interface': this._interfaceName,
      'filter': this._filterExpression
    };

    let commandObject: Object = {
      'start-sniffer': argumentsObject
    };

    this._remoteConnection.next(commandObject);
  }

}
