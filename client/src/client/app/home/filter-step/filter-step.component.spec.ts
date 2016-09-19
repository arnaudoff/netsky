import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { FilterStepComponent } from './filter-step.module';

export function main() {
   describe('Filter step component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [FilterStepModule]
      });
    });

    it('should have an input',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let filterStepDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(filterStepDOMElement.querySelectorAll('input').length).toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<filter-step></filter-step>'
})

class TestComponent {}
