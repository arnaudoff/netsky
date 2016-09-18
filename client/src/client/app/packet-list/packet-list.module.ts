import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from '../shared/shared.module';
import { PacketListComponent } from './packet-list.component';
import { SnifferClientService } from '../shared/sniffer-client/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [PacketListComponent],
  exports: [PacketListComponent],
  providers: [SnifferClientService]
})

export class PacketListModule { }
