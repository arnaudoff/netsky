import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';
import { Config } from '../config/env.config';

import { WebSocketService } from './../websocket/index';
import { Interface } from './interface';

@Injectable()
export class InterfaceService {

  public interfaces: Subject<Array<Interface>>;

  constructor(private wsService: WebSocketService) {
    this.interfaces = <Subject<Array<Interface>>>this.wsService
      .connect(Config.WS_SERVER_ADDRESS)
      .filter((response: MessageEvent) => {
          let data = JSON.parse(response.data);
          return data.hasOwnProperty('interfaces');
      })
      .map((response: MessageEvent) : Array<Interface> => {
        let data = JSON.parse(response.data);
        return <Array<Interface>>data.interfaces;
      });
  }

}
