import { Injectable } from '@angular/core';
import * as Rx from 'rxjs/Rx';

@Injectable()
export class WebSocketService {

  public activeConnection: Rx.Observable<Object>;

  private _subject: Rx.Subject<MessageEvent>;
  private _ws: WebSocket;

  public connect(url: string): Rx.Subject<MessageEvent> {
    this._ws = new WebSocket(url);
    this.activeConnection = Rx.Observable.fromEvent(this._ws, 'open');

    if (!this._subject) {
      this._subject = this.create(url);
    }

    return this._subject;
  }

  private create(url: string): Rx.Subject<MessageEvent> {
    let wsInstance = this._ws;

    let observable = Rx.Observable.create((observer: Rx.Observer<MessageEvent>) => {
      wsInstance.onmessage = observer.next.bind(observer);
      wsInstance.onerror = observer.error.bind(observer);
      wsInstance.onclose = observer.complete.bind(observer);

      return wsInstance.close.bind(wsInstance);
    });

    let observer = {
      next: (data: Object) => {
        if (wsInstance.readyState === WebSocket.OPEN) {
          wsInstance.send(JSON.stringify(data));
        }
      }
    };

    return Rx.Subject.create(observer, observable);
  }

}
