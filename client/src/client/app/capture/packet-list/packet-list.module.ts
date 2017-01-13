import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { VirtualScrollModule } from 'angular2-virtual-scroll';

import { SharedModule } from '../../shared/shared.module';
import { PacketListItemModule } from './packet-list-item/packet-list-item.module'

import { PacketListComponent } from './packet-list.component';
import { SnifferClientService } from '../../shared/sniffer-client/index';

@NgModule({
  imports: [CommonModule, SharedModule, VirtualScrollModule, PacketListItemModule],
  declarations: [PacketListComponent],
  exports: [PacketListComponent],
  providers: [SnifferClientService]
})
export class PacketListModule { }
