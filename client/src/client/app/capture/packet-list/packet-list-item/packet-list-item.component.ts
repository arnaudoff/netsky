import { Component, Input } from '@angular/core';

import { PacketListItem } from './packet-list-item'

/**
 * This class represents the lazy loaded PacketListItemComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'packet-list-item',
  templateUrl: 'packet-list-item.component.html',
  styleUrls: ['packet-list-item.component.css'],
})
export class PacketListItemComponent {
  @Input()
  item: PacketListItem;
}
