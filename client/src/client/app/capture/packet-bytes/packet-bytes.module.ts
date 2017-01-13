import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from '../../shared/shared.module';
import { PacketBytesComponent } from './packet-bytes.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [PacketBytesComponent],
  exports: [PacketBytesComponent]
})
export class PacketBytesModule { }
