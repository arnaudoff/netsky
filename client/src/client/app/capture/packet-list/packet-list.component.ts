import { Component } from '@angular/core';
import { SnifferClientService } from '../../shared/index';
import { PacketListItem } from './packet-list-item/packet-list-item';

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
  private receivedPackets: Array<Object> = [];
  private packetListItems: Array<PacketListItem> = [];

  /**
   * Creates an instance of the PacketListComponent with the injected
   * SnifferClientService.
   *
   * @param {SnifferClientService} snifferClientService - The injected SnifferClientService.
   */
  constructor(private snifferClientService: SnifferClientService) {
    this.snifferClientService.packets.subscribe(packet => {
      this.receivedPackets.push(packet);
      this.packetListItems.push(packet.summary);
    });
  }
}
