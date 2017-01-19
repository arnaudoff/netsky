import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { VirtualScrollModule } from 'angular2-virtual-scroll';

import { SharedModule } from '../../shared/shared.module';
import { PacketListItemModule } from './packet-list-item/packet-list-item.module'

import { SnifferService } from '../../shared/sniffer/index';
import { PacketService } from '../../shared/packet/index';
import { PacketListComponent } from './packet-list.component';

@NgModule({
  imports: [CommonModule, SharedModule, PacketListItemModule, VirtualScrollModule],
  declarations: [PacketListComponent],
  exports: [PacketListComponent],
  providers: [SnifferService, PacketService]
})
export class PacketListModule { }
