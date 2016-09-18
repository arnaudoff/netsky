import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';
import { WebSocketService } from './../websocket/index';

const SNIFFER_SERVER_URL = 'ws://localhost:3005';

@Injectable()
export class SnifferClientService {
  public packets: Subject<Object>;

  constructor(private wsService: WebSocketService) {
    this.packets = <Subject<Object>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .map((response: MessageEvent) : Object => {
        return JSON.parse(response.data);
      });
  }
}
