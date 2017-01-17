import { Component, ChangeDetectionStrategy, Input } from '@angular/core'; 

import { PacketListItem } from './../../../shared/sniffer-client/index';

/**
 * This class represents the lazy loaded PacketListItemComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'packet-list-item',
  templateUrl: 'packet-list-item.component.html',
  styleUrls: ['packet-list-item.component.css']
})
export class PacketListItemComponent {
  @Input()
  packet: PacketListItem;
}
