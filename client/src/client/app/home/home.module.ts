import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from '../shared/shared.module';

import { InterfaceStepModule } from './interface-step/interface-step.module';
import { FilterStepModule } from './filter-step/filter-step.module';
import { SharingStepModule } from './sharing-step/sharing-step.module';
import { StartStepModule } from './start-step/start-step.module';

import { HomeComponent } from './home.component';

@NgModule({
  imports: [
    CommonModule, SharedModule, InterfaceStepModule, FilterStepModule,
    SharingStepModule, StartStepModule],
  declarations: [HomeComponent],
  exports: [HomeComponent]
})

export class HomeModule { }
