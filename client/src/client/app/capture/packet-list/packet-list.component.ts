import { Component, ViewChild } from '@angular/core';

import { SnifferClientService } from '../../shared/index';
import { PacketListItem } from './../../shared/sniffer-client/index';

import { VirtualScrollComponent } from 'angular2-virtual-scroll';

/**
 * This class represents the lazy loaded PacketListComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'packet-list',
  templateUrl: 'packet-list.component.html',
  styleUrls: ['packet-list.component.css'],
})
export class PacketListComponent {
  private receivedPackets: Array<PacketListItem> = [];

  @ViewChild(VirtualScrollComponent)
  private virtualScroll: VirtualScrollComponent;

  /**
   * Creates an instance of the PacketListComponent with the injected
   * SnifferClientService.
   *
   * @param {SnifferClientService} snifferClientService - The injected SnifferClientService.
   */
  constructor(private snifferClientService: SnifferClientService) {
    this.snifferClientService.packets.subscribe(packet => {
      this.receivedPackets.push(packet);
      this.virtualScroll.refresh();
    });
  }
}
