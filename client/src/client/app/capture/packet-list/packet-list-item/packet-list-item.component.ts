import { Component, ChangeDetectionStrategy, Input } from '@angular/core'; 

import { Packet } from './../../../shared/packet/index';

@Component({
  moduleId: module.id,
  selector: 'packet-list-item',
  templateUrl: 'packet-list-item.component.html',
  styleUrls: ['packet-list-item.component.css']
})
export class PacketListItemComponent {
  @Input()
  packet: Packet;
}
