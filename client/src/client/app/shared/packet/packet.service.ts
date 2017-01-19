import { Injectable } from '@angular/core';
import { Observable, Subject, BehaviorSubject } from 'rxjs/Rx';
import { Config } from '../config/env.config';

import { WebSocketService } from './../websocket/index';
import { Packet } from './packet';

@Injectable()
export class PacketService {

  private _observedPacket: BehaviorSubject<Packet> = new BehaviorSubject({});

  public packets: Subject<Packet>;

  constructor(private wsService: WebSocketService) {
    this.packets = <Subject<Packet>>this.wsService
      .connect(Config.WS_SERVER_ADDRESS)
      .map((response: MessageEvent) : Packet => {
        let data = JSON.parse(response.data);
        return <Packet>data;
      });
  }

  get observedPacket() : Observable<Packet> {
    return this._observedPacket.asObservable();
  }

  public setObservedPacket(packet: Packet) {
    this._observedPacket.next(packet);
  }

}
