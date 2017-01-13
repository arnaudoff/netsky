import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from '../../../shared/shared.module';
import { PacketListItemComponent } from './packet-list-item.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [PacketListItemComponent],
  exports: [PacketListItemComponent]
})
export class PacketListItemModule { }
