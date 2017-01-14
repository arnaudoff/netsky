import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../shared/shared.module';
import { SharingStepComponent } from './sharing-step.component';
//import { SnifferClientService } from '../shared/sniffer-client/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [SharingStepComponent],
  exports: [SharingStepComponent]
  //providers: [SnifferClientService]
})
export class SharingStepModule { }
