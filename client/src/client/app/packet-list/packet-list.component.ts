import { Component } from '@angular/core';
import { SnifferClientService } from '../shared/index';
import { PacketListEntry } from './packet-list-entry.model';

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
  private packetList: Array<PacketListEntry> = [];

  /**
   * Creates an instance of the PacketListComponent with the injected
   * SnifferClientService.
   *
   * @param {SnifferClientService} snifferClientService - The injected SnifferClientService.
   */
  constructor(private snifferClientService: SnifferClientService) {
    this.snifferClientService.packets.subscribe(packet => {
      this.receivedPackets.push(packet);

      // map somehow
    });
  }
}
