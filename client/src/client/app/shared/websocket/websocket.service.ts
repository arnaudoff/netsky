import { Injectable } from '@angular/core';
import * as Rx from 'rxjs/Rx';

@Injectable()
export class WebSocketService {

  public activeConnection: Rx.Observable<Object>;

  private subject: Rx.Subject<MessageEvent>;
  private ws: WebSocket;

  public connect(url: string): Rx.Subject<MessageEvent> {
    this.ws = new WebSocket(url);
    this.activeConnection = Rx.Observable.fromEvent(this.ws, 'open');

    if (!this.subject) {
      this.subject = this.create(url);
    }

    return this.subject;
  }

  private create(url: string): Rx.Subject<MessageEvent> {
    let wsInstance = this.ws;

    let observable = Rx.Observable.create((observer: Rx.Observer<MessageEvent>) => {
      // Emit the received message to the observer
      wsInstance.onmessage = observer.next.bind(observer);

      wsInstance.onerror = observer.error.bind(observer);
      wsInstance.onclose = observer.complete.bind(observer);

      // Close the websocket on unsubscribe
      return wsInstance.close.bind(wsInstance);
    });

    let observer = {
      next: (data: Object) => {
        if (wsInstance.readyState === WebSocket.OPEN) {
          console.log('just sent ' + JSON.stringify(data));
          wsInstance.send(JSON.stringify(data));
        }
      }
    };

    return Rx.Subject.create(observer, observable);
  }

}
