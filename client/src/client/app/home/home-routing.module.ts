import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';

import { HomeComponent } from './home.component';

import { InterfaceStepComponent } from './interface-step/interface-step.component'
import { FilterStepComponent } from './filter-step/filter-step.component'
import { StartStepComponent } from './start-step/start-step.component'

@NgModule({
  imports: [
    RouterModule.forChild([
      {
        path: 'new',
        component: HomeComponent,
        children: [
          { path: '', redirectTo: 'interface', pathMatch: 'full' },
          { path: 'interface', component: InterfaceStepComponent },
          { path: 'filter', component: FilterStepComponent },
          { path: 'start', component: StartStepComponent }
        ]
      }
    ])
  ],
  exports: [RouterModule]
})
export class HomeRoutingModule { }
