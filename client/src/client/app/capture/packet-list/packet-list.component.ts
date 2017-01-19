import { Component, ViewChild } from '@angular/core';
import { VirtualScrollComponent, ChangeEvent } from 'angular2-virtual-scroll';

import { PacketService } from '../../shared/index';
import { Packet } from './../../shared/packet/index';

@Component({
  moduleId: module.id,
  selector: 'packet-list',
  templateUrl: 'packet-list.component.html',
  styleUrls: ['packet-list.component.css'],
})
export class PacketListComponent {

  private packetsBuffer: Packet[] = [];
  private renderablePackets: Packet[] = [];
  private totalReceived: number = 0;
  private readonly viewPortSize: number = 15;
  private indices: ChangeEvent;

  @ViewChild(VirtualScrollComponent)
  private virtualScroll: VirtualScrollComponent;

  constructor(private packetService: PacketService) {
    this.packetService.packets.subscribe((packet: Packet) => {
      this.totalReceived += 1;

      if (this.totalReceived < this.viewPortSize) {
        this.renderablePackets.push(packet);
      } else if (this.totalReceived === this.viewPortSize) {
        this.virtualScroll.refresh();
      } else {
        this.packetsBuffer.push(packet);
      }
    });
  }

  private onListChange(event: ChangeEvent) {
    this.indices = event;

    if (event.end === this.renderablePackets.length) {
      let packetsToTake = (this.packetsBuffer.length < this.viewPortSize) ?
        this.packetsBuffer.length : this.viewPortSize;

      for (let i = 0; i < packetsToTake; i += 1) {
        this.renderablePackets.push(this.packetsBuffer.shift());
      }

      this.virtualScroll.refresh();
    }
  }

  private packetClicked(packet: Packet) {
    this.packetService.setObservedPacket(packet);
  }

}
