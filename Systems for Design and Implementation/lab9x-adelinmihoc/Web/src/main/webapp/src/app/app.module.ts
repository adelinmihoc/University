import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import {HttpClientModule} from "@angular/common/http";
import {AppRoutingModule} from "./app-routing/app-routing.module";
import {FormsModule, ReactiveFormsModule} from "@angular/forms";
import {BrowserAnimationsModule} from "@angular/platform-browser/animations";
import {RouterModule, ActivatedRoute, ParamMap} from "@angular/router";

import { MatInputModule} from "@angular/material/input";
import { MatSelectModule} from "@angular/material/select";
import { MatButtonModule} from "@angular/material/button";
import { MatCheckboxModule} from "@angular/material/checkbox";
import { MatChipsModule} from "@angular/material/chips";
import {MatTableModule} from "@angular/material/table";
import {MatPaginatorModule} from "@angular/material/paginator";
import {MatSortModule} from "@angular/material/sort";
import {MatMenuModule} from '@angular/material/menu';

import { AddressesComponent } from './addresses/addresses.component';
import { AddressListComponent } from './addresses/address-list/address-list.component';
import {AddressService} from "./addresses/shared/address.service";
import { CoffeesComponent } from './coffees/coffees.component';
import { CoffeeListComponent } from './coffees/coffee-list/coffee-list.component';
import { CustomersComponent } from './customers/customers.component';
import { CustomerListComponent } from './customers/customer-list/customer-list.component';
import { OrdersComponent } from './orders/orders.component';
import { OrderListComponent } from './orders/order-list/order-list.component';
import { OrderAddComponent } from './orders/order-add/order-add.component';
import { AddressAddComponent } from './addresses/address-add/address-add.component';
import { AddressDeleteComponent } from './addresses/address-delete/address-delete.component';
import { AddressUpdateComponent } from './addresses/address-update/address-update.component';
import {CoffeeService} from "./coffees/shared/coffee.service";
import {CustomerService} from "./customers/shared/customer.service";
import {OrderService} from "./orders/shared/order.service";

import {
  MatIconModule,
} from '@angular/material/icon';
import { CoffeeAddComponent } from './coffees/coffee-add/coffee-add.component';
import { CoffeeDeleteComponent } from './coffees/coffee-delete/coffee-delete.component';
import { CoffeeUpdateComponent } from './coffees/coffee-update/coffee-update.component';
import { CoffeeFilterComponent } from './coffees/coffee-filter/coffee-filter.component';
import { FilterPipe } from './coffees/shared/filter.pipe';
import { CustomerAddComponent } from './customers/customer-add/customer-add.component';
import { CustomerDeleteComponent } from './customers/customer-delete/customer-delete.component';
import { CustomerUpdateComponent } from './customers/customer-update/customer-update.component';
import { CustomerFilterComponent } from './customers/customer-filter/customer-filter.component';
import { OrderDeleteComponent } from './orders/order-delete/order-delete.component';
import { OrderUpdateComponent } from './orders/order-update/order-update.component';
import { OrderFilterComponent } from './orders/order-filter/order-filter.component';

@NgModule({
  declarations: [
    AppComponent,
    AddressesComponent,
    AddressListComponent,
    CoffeesComponent,
    CoffeeListComponent,
    CustomersComponent,
    CustomerListComponent,
    OrdersComponent,
    OrderListComponent,
    OrderAddComponent,
    AddressAddComponent,
    AddressDeleteComponent,
    AddressUpdateComponent,
    CoffeeAddComponent,
    CoffeeDeleteComponent,
    CoffeeUpdateComponent,
    CoffeeFilterComponent,
    FilterPipe,
    CustomerAddComponent,
    CustomerDeleteComponent,
    CustomerUpdateComponent,
    CustomerFilterComponent,
    OrderDeleteComponent,
    OrderUpdateComponent,
    OrderFilterComponent,
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    AppRoutingModule,
    RouterModule,

    ReactiveFormsModule,
    BrowserAnimationsModule,
    ReactiveFormsModule,
    BrowserAnimationsModule,
    MatInputModule,
    MatButtonModule,
    MatSelectModule,
    MatCheckboxModule,
    MatChipsModule,
    MatTableModule,
    MatSortModule,
    MatPaginatorModule,
    MatMenuModule,
    MatIconModule,
    FormsModule,
  ],
  providers: [AddressService, CoffeeService, CustomerService, OrderService],
  bootstrap: [AppComponent]
})
export class AppModule { }
