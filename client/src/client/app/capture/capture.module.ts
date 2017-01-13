import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from '../shared/shared.module';
import { CaptureRoutingModule } from './capture-routing.module';
import { PacketListModule } from './packet-list/packet-list.module';
import { PacketDetailsModule } from './packet-details/packet-details.module';
import { PacketBytesModule } from './packet-bytes/packet-bytes.module';

import { CaptureComponent } from './capture.component';

@NgModule({
  imports: [
    CommonModule, SharedModule, PacketListModule, PacketDetailsModule,
    PacketBytesModule, CaptureRoutingModule
  ],
  declarations: [CaptureComponent],
  exports: [CaptureComponent]
})
export class CaptureModule { }
