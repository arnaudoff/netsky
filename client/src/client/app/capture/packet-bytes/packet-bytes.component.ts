import { Component } from '@angular/core';

import { PacketService, Packet } from './../../shared/packet/index';

@Component({
  moduleId: module.id,
  selector: 'packet-bytes',
  templateUrl: 'packet-bytes.component.html'
})
export class PacketBytesComponent {

  private bytesToDisplay: string = null;

  constructor(private packetService: PacketService) {
    packetService.observedPacket.subscribe((packet: Packet) => {
      if (packet.hasOwnProperty('payload') &&
          packet.payload.hasOwnProperty('contents')) {
        this.bytesToDisplay = packet.payload.contents;
      }
    });
  }

}
