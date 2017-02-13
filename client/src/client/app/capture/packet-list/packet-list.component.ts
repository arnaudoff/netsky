import { Component, ViewChild } from '@angular/core';
import { VirtualScrollComponent, ChangeEvent } from 'angular2-virtual-scroll';

import { Packet } from './../../shared/packet/index';
import { PacketService } from '../../shared/index';
import { SnifferService } from '../../shared/sniffer/index';

@Component({
  moduleId: module.id,
  selector: 'packet-list',
  templateUrl: 'packet-list.component.html',
  styleUrls: ['packet-list.component.css'],
})
export class PacketListComponent {

  public readonly viewPortSize: number = 15;
  public renderablePackets: Packet[] = [];
  public indices: ChangeEvent;
  public filterExpression: string = '';

  private totalReceived: number = 0;
  private receivedPacketsBuffer: Packet[] = [];

  private packetsBuffer: Packet[] = [];
  private filteredPacketsBuffer: Packet[] = [];

  @ViewChild(VirtualScrollComponent)
  private virtualScroll: VirtualScrollComponent;

  constructor(private packetService: PacketService,
              private snifferService: SnifferService) {
    this.packetService.packets.subscribe((packet: Packet) => {
      this.totalReceived += 1;

      if (this.totalReceived < this.viewPortSize) {
        this.renderablePackets.push(packet);
      } else if (this.totalReceived === this.viewPortSize) {
        this.virtualScroll.refresh();
      } else {
        if (this.filterExpression.length > 0) {
          if (this.packetService.filterSingle(packet, this.filterExpression)) {
            this.filteredPacketsBuffer.push(packet);
          }
        } else {
          this.packetsBuffer.push(packet);
        }

        this.receivedPacketsBuffer.push(packet);
      }
    });
  }

  private packetClicked(packet: Packet) {
    this.packetService.setObservedPacket(packet);
  }

  private applyFilter(filterExpression: string) {
    try {
      let expression = JSON.parse(filterExpression);
    } catch (e) {
      alert('The supplied filter is invalid.');
    }

    this.filterExpression = filterExpression;
    this.renderablePackets = [];

    this.filteredPacketsBuffer = this.packetService.filterCollection(
      this.receivedPacketsBuffer, filterExpression);

    this.shiftBufferToRenderable(this.filteredPacketsBuffer);
  }

  private clearFilter(): void {
    this.filterExpression = '';
    this.renderablePackets = [];

    this.packetsBuffer = this.receivedPacketsBuffer.slice();
    this.shiftBufferToRenderable(this.packetsBuffer);
  }

  private onListChange(event: ChangeEvent) {
    this.indices = event;

    if (event.end === this.renderablePackets.length) {
      let buffer: Packet[];

      if (this.filterExpression.length > 0) {
        buffer = this.filteredPacketsBuffer;
      } else {
        buffer = this.packetsBuffer;
      }

      this.shiftBufferToRenderable(buffer);
    }
  }

  private shiftBufferToRenderable(sourceBuffer: Packet[]) : void {
    let packetsToTake = (sourceBuffer.length < this.viewPortSize) ?
      sourceBuffer.length : this.viewPortSize;

    for (let i = 0; i < packetsToTake; i += 1) {
      this.renderablePackets.push(sourceBuffer.shift());
    }

    this.virtualScroll.refresh();
  }

  private stop() {
    this.snifferService.stop();
  }

}
