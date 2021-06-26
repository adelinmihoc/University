import { ComponentFixture, TestBed } from '@angular/core/testing';

import { FilterDestinationsComponent } from './filter-destinations.component';

describe('FilterDestinationsComponent', () => {
  let component: FilterDestinationsComponent;
  let fixture: ComponentFixture<FilterDestinationsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ FilterDestinationsComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(FilterDestinationsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
