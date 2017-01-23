import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../../shared/shared.module';
import { FilterStepComponent } from './filter-step.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [FilterStepComponent],
  exports: [FilterStepComponent]
})
export class FilterStepModule { }
