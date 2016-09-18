import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PacketListModule } from '../packet-list/packet-list.module';
import { SharedModule } from '../shared/shared.module';
import { CaptureComponent } from './capture.component';

@NgModule({
  imports: [CommonModule, SharedModule, PacketListModule],
  declarations: [CaptureComponent],
  exports: [CaptureComponent]
})

export class CaptureModule { }
