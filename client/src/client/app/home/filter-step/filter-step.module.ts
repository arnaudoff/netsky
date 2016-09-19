import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from './../../shared/shared.module';
import { FilterStepComponent } from './filter-step.component';
//import { SnifferClientService } from '../shared/sniffer-client/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [FilterStepComponent],
  exports: [FilterStepComponent]
//  providers: [SnifferClientService]
})

export class FilterStepModule { }
