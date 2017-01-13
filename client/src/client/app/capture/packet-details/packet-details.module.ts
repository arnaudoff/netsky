import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from '../../shared/shared.module';
import { PacketDetailsComponent } from './packet-details.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [PacketDetailsComponent],
  exports: [PacketDetailsComponent]
})
export class PacketDetailsModule { }

